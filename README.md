# sx1231-dll

A lightweight, bare-metal **Data Link Layer (DLL) and Physical Layer (PHY)** firmware stack written in C99 for **ATmega644P** microcontrollers paired with **Semtech SX1231 / RFM69** sub-GHz (868 MHz) transceivers.

Designed with hardware-independent protocol modules so core framing, byte-stuffing, and error-detection logic can be unit-tested natively on a host machine (`gcc`) before cross-compiling (`avr-gcc`) and flashing to target hardware.

---

## Architecture & Target Platform

| Component | Specification |
| :--- | :--- |
| **MCU** | Microchip AVR ATmega644P @ 12 MHz (`-DF_CPU=12000000UL`) |
| **RF Transceiver** | Semtech SX1231 / RFM69 (868 MHz ISM band, SPI interface) |
| **Language / Standard** | C99 (`-std=c99 -Os -Wall`) |
| **Build & Flash** | `avr-gcc`, `avr-objcopy`, `avr-size`, `avrdude` (`usbasp`) |
| **Host Testing** | Native `gcc` assertion-based unit test suite (`make test`) |

---

## Protocol Specifications

All protocol parameters are centralized in [`include/config.h`](include/config.h):

- **Framing & Transparency:** Delimited by `0x7E` (`FLAG_BYTE`) with byte-level escaping using `0xAA` (`ESCAPE_BYTE`).
- **Payload & Fragmentation:** `23` bytes max payload per frame, up to `4` fragments (`92` bytes max reassembled packet); broadcast address `0x00`.
- **Error Detection:**
  - **16-bit One's-Complement Checksum (`sum16`):** Low-overhead additive integrity check.
  - **CRC-16-CCITT (`crc16`):** Init `0xFFFF`, polynomial `0x1021` (verified against the standard `"123456789"` → `0x29B1` check value).
- **Reliability (ARQ):** `150 ms` ACK timeout, up to `3` retransmissions.
- **Medium Access (CSMA):** p-persistent CSMA (`p = 80%`) with `-90 dBm` busy-channel threshold.

### Control Byte Bit Layout

| Bit | Macro | Purpose |
| :---: | :--- | :--- |
| `0` | `BIT_FRAME_TYPE` | Frame type indicator (Data / Control) |
| `1` | `BIT_SEQ` | Sequence number bit |
| `2` | `BIT_ACK` | Acknowledgment flag |
| `3` | `BIT_MORE_FRAGS` | Indicates additional fragments follow |
| `4–5` | `BIT_FRAG_INDEX` | 2-bit fragment index (`0–3`) |
| `6` | `BIT_CRC_ENABLE` | Selects CRC-16-CCITT vs. 16-bit checksum |

---

## Repository Structure

```text
sx1231-dll/
├── include/
│   ├── config.h          # Protocol constants, bitfields, ARQ/CSMA/RF parameters
│   ├── checksum.h        # sum16 and CRC-16-CCITT interfaces
│   └── stuff.h           # Byte-stuffing / unstuffing interfaces
├── src/
│   ├── main.c            # Embedded firmware entry point
│   ├── checksum.c        # 16-bit checksum and CRC-16-CCITT implementations
│   └── stuff.c           # Framing escape/unescape implementations
├── lib/
│   ├── RFM69.*           # SX1231 / RFM69 transceiver driver & register map
│   ├── spi.*             # AVR hardware SPI driver
│   ├── uart.*            # Debug UART0 serial output driver
│   ├── millis.*          # Millisecond system timer for timeouts & ARQ
│   └── xorrand.*         # Lightweight PRNG for CSMA backoff / persistence
├── test/
│   ├── test_config.c     # Compile-time/config invariant & bitfield checks
│   ├── test_checksum.c   # Checksum & CRC-16-CCITT test vectors
│   └── test_stuff.c      # Stuffing, unstuffing, and worst-case expansion tests
└── Makefile              # Host test, AVR cross-compile, and flash targets
```

---

## Getting Started

### Prerequisites

- **Host unit tests:** `gcc`, `make`
- **Target firmware build & flash:** `avr-gcc`, `avr-binutils` (`avr-objcopy`, `avr-size`), `avr-libc`, `avrdude`, and a USBasp programmer

### Run Host Unit Tests

Run all hardware-independent protocol tests locally on your machine:

```bash
make test
```

This compiles and executes:
1. **`test_config`** — Verifies maximum packet capacity (`MAX_PAYLOAD * MAX_FRAGMENTS == 92`) and non-overlapping control byte bit positions.
2. **`test_checksum`** — Verifies single-bit flip detection in `sum16`, the official `0x29B1` check value for `crc16("123456789")`, and CRC-16's ability to detect byte-order swaps that additive checksums miss.
3. **`test_stuff`** — Verifies `0x7E` escaping, `stuff()` → `unstuff()` round-trip fidelity, `0xAA` self-escaping, and worst-case 2× expansion (`30` bytes of `0x7E` → `60` bytes).

### Build Firmware for ATmega644P

```bash
make build
```

Generates `obj/main.elf`, `obj/main.hex`, and prints flash/RAM memory usage via `avr-size`.

### Flash to Target Hardware

```bash
make flash
```

Builds the firmware and flashes `obj/main.hex` to the ATmega644P via `usbasp`.

### Clean Build Artifacts

```bash
make clean
```

---

## Implementation Status

- [x] Protocol configuration & control-byte bitfield definitions (`config.h`)
- [x] 16-bit additive checksum (`sum16`) and CRC-16-CCITT (`crc16`) with unit tests
- [x] Byte-stuffing (`stuff`) and unstuffing (`unstuff`) with unit tests
- [x] AVR cross-compilation, hex generation, and USBasp flashing pipeline
- [x] Low-level hardware drivers (SX1231/RFM69, SPI, UART0, `millis`, `xorrand`)
- [ ] Frame serialization / deserialization state machine
- [ ] Stop-and-Wait ARQ & fragmentation/reassembly
- [ ] p-Persistent CSMA MAC integration over SX1231
