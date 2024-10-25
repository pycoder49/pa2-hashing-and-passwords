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
