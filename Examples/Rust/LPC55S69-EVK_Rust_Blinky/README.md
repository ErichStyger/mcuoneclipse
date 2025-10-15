# Rust for LPC55S69
Project for the NXP LPC55S69-EVK using Rust with Embassy.
Articles:
- https://mcuoneclipse.com/2025/10/15/getting-started-with-rust-on-nxp-lpc55s69-evk/

Check out the blog article(s) for more details.

## Updating and Toolchains
Update:
```
$ rustup update
```
Check installed toolchains:
```
$ rustup show
```

## probe-rS
https://probe.rs/ 
https://mcuoneclipse.com/2024/03/17/nxp-mcu-link-for-rust-with-probe-rs/ 
https://probe.rs/docs/getting-started/installation/

Build and install from sources:
```
$ cargo install probe-rs-tools --locked
```
Install the binary utilities:
```
$ cargo install cargo-binutils
```
List connected probes:
```
$ probe-rs list
```

## Embassy and LPC55S69
https://github.com/embassy-rs/embassy
```
$ git clone https://github.com/embassy-rs/embassy.git
$ cd embassy/examples/lpc55s69
$ cargo build
$ cargo run --bin blinky_nop
```
- blinky_nop: Blink the integrated RED LED using nops as delay. Useful for flashing simple and known-good software on board.
- button_executor: Turn on/off an LED by pressing the USER button. Demonstrates how to use the PINT and GPIO drivers.
- blinky_embassy_time: Blink the integrated RED LED using `embassy-time`. Demonstrates how to use the time-driver that uses RTC. 

NOTE: button example does not work? Noted in the example readme, need to re-power the board.
