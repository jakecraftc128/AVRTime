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
| validGivenTime(hour, minute, startHour, startMin, endHour, endMin) | int, int, int, int, int, int | true/false | Returns true if the given time (`hour`, `minute`) falls in the given time window
| timeUpdate() | none | true/false | Returns true if `seconds` has updated since last call |
| getSecond() | none | Any integer 0-59 | Returns the current stored `second` |
| getMinute() | none | Any integer 0-59 | Returns the current stored `minute` |
| getHour(hour12Time) | boolean | Any integer 0-23 if `hour12Time` is `false`, Any integer 0-12 if `hour12Time` is `true` | Returns the current stored `hour` |
| getDate() | none | Any integer 0-[End of current month] | Returns the current stored `day` (of the month) |
| getMonth() | none | Any integer 0-12 | Returns the current stored `month` |
| getYear() | none | Any integer 0-9999 | Returns the current stored `year` |
| parseSec() | none | Any number as a String "0"-"59" | Returns the current stored `second` as a `String` |
| parseMin() | none | Any number as a String "0"-"59" | Returns the current stored `minute` as a `String` |
| parseHour() | none | Any number as a String "0"-"23" | Returns the current stored `hour` as a `String` |
| parseDay() | none | Any number as a String "0"-"[End of current month]" | Returns the current stored `day` as a `String` |
| parseMonth() | none | Any Month "JAN"-"DEC" | Returns the current stored `month` as a `String` (not like a number, but rather JAN or MAR) |
| parseYear() | none | Any number as a String "0"-"9999" | Returns the current stored `year` as a `String` |

(i) A good use for the `parse ***` functions would be to use them as the arguments for the `setStringTime`/`setStringDate` functions, since their return type is a `String`
