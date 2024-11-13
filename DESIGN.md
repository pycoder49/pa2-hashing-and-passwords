Real password crackers try many more variations than just uppercasing and lowercasing. Do a little research on password cracking and suggest at least 2 other ways to vary a password to crack it. Describe them both, and for each, write a sentence or two about what modifications you would make to your code to implement them.

Answer:
1) Using symbols. Symbols like @#$%^&, etc. This would allow many other millions of password combinations.
And the crack them, I would add more conditions in my function which would look out for these. If there are characters within a certain rnge of numbers from ASCII, I would most likely check for the range, or perhaps check for ranges in UTF-8. Or, I could also check for simliar characters. For example, when checking for 'a', I could also check for "@", and 's' with '$', etc.

2) Another way to vary a password is with using a combinations of word. A lot of people tend to uppercase the starting letter of a specific word in the passward. Something like: PizzaCarBox, or SizzlingBearForest.
To crack these kinds of passwords, I could change my program to look for uppercase ASCII letters. If a uppercased ascii letter is found, I could get that word and have it be traversed through a list of common words, to see if there are any matches.


How much working memory is needed to store all of the variables needed to execute the password cracker? Based on your response would you say that a password cracker is more memory-limited or is it more limited by how fast the process can run the code?

Answer:
The working memory eneded is a variable amount. depending on the length of passwords, both the memoty needed to store and the computaion power would be different. But to estimate, we know SHA length is 32 bytes, the hex hash has 64 bytes plus a null terminator, which would then make it 65 bytes. All variables that were declared as a char in the program, including the ones inside the for-loop will be of 1 byte.

Based on the response above, I believe that the program is more limited by its runtime execution speed. Since it has a fairly low memory usage, it will not cause any trouble in memory handling. However, what could affect its performance is its speed. Based on the algorithms used, the program could either compare hashes slower or faster.



UPDATED DESIGN QUESTION:

Consider the following run of your updated pwcrack:

$ ./pwcrack b54051d1abdba8656126f85f96d9270283d34b1cb8787b78c50646d9eb4a502d
secret118
secret111
<Press Ctrl-D for end of input>
Did not find a matching password

1) How many password variations were hashed and tested for a match?

- We start from the first character and then make it uppercase (one at a time) --> 6 count
    {Secret118, sEcret118, seCret118, secRet118, secrEt118, secreT118}
- Then, when it gets to the digits, it starts from 0-9 for each digit --> 10*3 = 30 count
    {secret018, ...118, ...218, ..., ...918}
    {secret108, ...128, 138, ..., ...198}
    {secret110, ...112, ...113, ..., 119}

- Total count for `secret118` input: 6 + 30 = 36

- for two tried, we do 36*2 = 72 total variations



2) How many duplicate password variations were hashed and checked?

- For the first password, hare are all the numbers checked:

{
018, 118, 218, 318, 418, 518, 618, 718, 818, 918,
108, 118, 128, 138, 148, 158, 168, 178, 188, 198,
110, 111, 112, 113, 114, 115, 116, 117, 118, 119
}

where the first row shows the variants of 0-9 for the first number, second row for the second number, and third row for the third number.

From this we can see that all three rows have the number 118, making it a total of 2 duplicates.


- For the second password, here are all the numbers checked:

{
011, 111, 211, 311, 411, 511, 611, 711, 811, 911,
101, 111, 121, 131, 141, 151, 161, 171, 181, 191,
110, 111, 112, 113, 114, 115, 116, 117, 118, 119
}

where the first row shows the variants of 0-9 for the first number, second row for the second number, and the third row for the third number.

From this we can see that all three rows share the number 111, making it a total of 2 duplicates.



3) What are ways you might change your implementation to avoid this repeated and redundant work?

One way to skip over these redundancies is to use a hash table, where everytime you encounter a unique variant, you'd store it in the table. If the one you're going to test is already in the table, skip over it and go to the next variant.

There could be a second way for this specific situation. When we get to the second digit (in our case), we can avoid hashing the original number. For example, 

- first digit variation: secret118

- When we are checking the second digit, we can jump from hashing "secret108" to "secret128", avoiding hashing the original "1" that we had in the input. And the same for the third digit: we could jump from "secret117" to "secret119" since we already know that "secret118" has been hashed and checked.
