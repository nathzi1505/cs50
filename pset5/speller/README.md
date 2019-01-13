# Questions

## What is pneumonoultramicroscopicsilicovolcanoconiosis?

The longest word in the english dictionary.

## According to its man page, what does `getrusage` do?

It finds the resource usage, the process took to complete.

## Per that same man page, how many members are in a variable of type `struct rusage`?

16 members are present.

## Why do you think we pass `before` and `after` by reference (instead of by value) to `calculate`, even though we're not changing their contents?

So as to allow the change/storage to happen in the original copy of the variables `before` and `after` thus making calculations easier.

## Explain as precisely as possible, in a paragraph or more, how `main` goes about reading words from a file. In other words, convince us that you indeed understand how that function's `for` loop works.

Well, `main` starts analyzing words character by character. `main` does it in the following steps.

1. It reads a character from the `file`.

2. Checks whether the character is
    a. alphabet 'or'
    b. an apostrophe provided the apostrophe is not the first character.
   If a 'or' b checks out to be `true` then `main` appends the character to the word.
catch : If the index (i.e. length of the word) is found to be greater than the longest word then the next characters are consumed/ignored until something else 'other' than an alphabet is encountered. (The index is re initialised zero).

3. If the character is found to be numeric then the rest of the characters after that are ignored until something else 'other' than a digit/alphabet is encountered.(The index is re initialised zero)

4. If something else (a white space ' ' maybe) is encountered, a nul character '\0' is appended and the word string is complete and the word counter incremented.

5. The index is made zero and the process continues from step '1'.

## Why do you think we used `fgetc` to read each word's characters one at a time rather than use `fscanf` with a format string like `"%s"` to read whole words at a time? Put another way, what problems might arise by relying on `fscanf` alone?

`fgetc` helps to read words character by character. However, `fscanf` although may work, might cause problems if the found string is not in proper specifications as that of the format string i.e. what if words are seperated with periods (.) then `fscanf` will consider it to be a single string.

## Why do you think we declared the parameters for `check` and `load` as `const` (which means "constant")?

So that anyhow the original values/parameters should not change as such.
