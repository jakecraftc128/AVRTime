# AVRTime


Arduino library for keeping time without an RTC

**IMPORTANT: Make sure you're calling `time.keepTime()` in `void loop()` to keep time**

## Supported boards as of yet:

#### [AVR]
- [x] Arduino UNO
- [x] Arduino Mega
- [x] Arduino Nano

#### [mBed OS]
- [ ] Arduino Nano BLE 33
- [ ] Arduino Nano RP2040 Connect (RP2040  Architecture)

## Library Functions with Description

**Make sure to enstanciate the time object using `AVRTimer time;`**

**All the following are functions of the `time` object (`time.*`)**

| Function Name | Argument Data Types | Returned Values | Description |
|---------------|---------------------|-----------------|-------------|
| begin()       | none | none | Fills in the time and date to be used later. |
| setTime(hour, minute, second) | int, int, int | none | Changes or adjusts the stored time. |
| setStringTime(hour, minute, second) | String, String, String | none | Changes or adjusts the stored time with `String` values. (`"02"` instead of `02`) |
| setDate(month, day, year) | int, int, int | none | Changes or adjusts the date. **Note:** The `year` argument is 4 digits in length (20xx) |
| setStringDate(month, day, year) | String, String, String | none | Changes or adjusts the date with `String` values. (`"20xx"` instead of `20xx`) |
| printFormattedTime(&Serial) | Print (Serial) | Not directly; through Serial | Prints the current date and time, formatted |
| validTime(startHour, startMin, endHour, endMin) | int, int, int, int | true/false | Returns true if the current time falls in the given time window (Start --> End) |
| validGivenTime( |
