# Questions

## What's `stdint.h`?

It is a C standard library which includes `typedef`s that specify exact width primitive data types along with defined maximum and minimum values for each type, so as to make the code more portable.

## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?

The person reading the code will immediately know the datatype and the size of the datatype (in bits).

## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?

`BYTE` is 1 Byte, `DWORD` is 4 Bytes, `LONG` is 4 Bytes, `WORD` is 2 Bytes.

## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."

`Ox42` and `0x4D`

## What's the difference between `bfSize` and `biSize`?

`bfSize` is the size of bytes required by the bitmap file while `biSize` is the size of bytes required by the structure (ie. `BITMAPINFOHEADER`).

## What does it mean if `biHeight` is negative?

It indicates a top-down DIB (Device Independent Bitmap) and it starts from the top-left corner.

## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?

`biBitCount`.

## Why might `fopen` return `NULL` in lines 24 and 32 of `copy.c`?

In line 24, `fopen` may return a `NULL` if the file `infile` does not exist all on the disk.
In line 32, `fopen` may return a `NULL` if file `outfile` could not be created.

## Why is the third argument to `fread` always `1` in our code?

`1` means unit number of blocks of `sizeof(...)` is read.

## What value does line 65 of `copy.c` assign to `padding` if `bi.biWidth` is `3`?

`3` (ie `3` Bytes of padding is present).

## What does `fseek` do?

`fseek` helps to change the location  of the file pointer.

## What is `SEEK_CUR`?

It helps to set the file pointer in relation to the Current position.

## Whodunit?

It was Professor Plum with the candle stick in the library.
