BILLY is a lightweight, low-dependency chatbot designed to bring basic chat and semantic understanding capability to the world of embedded. It is broken down into modules, including "text data" "text clean", "text train", "text tag", and "text stem" which build upon each other to process everyday speech and extract increasingly complex information from it. An explanation of each module is below.

Text Data: Simply returns information about the text such as text length, whether it contains a number, and other information necessary for the other modules to function. This module has little use on its own and serves mainly to support the other modules.

Text Clean: Converts the text into a form for the other modules to process. It removes unnecessary parts of the text such as numerals and punctuation, tokenizes the text into individual words, and provides functionality to copy and append text. Please note that other than"Append_Text" and "Append_Word", all text_clean functions either kkeep the text the same size or reduce it.

Text Train: This module populates an SQLite database that is used to train the model in "text tag". It takes part-of-speech tagged text that is delimited by an underscore (with the format "word_tag") and counts how many times each word is associated with a tag as well as how many times each tag follows each other tag. It also totals the word counts and tag counts and uses that data to calculate the likelihood that any given word is a particular part of speech, as well as the liklihood that a given part of speech will be followed by another part of speech.

Text Tag:

Text Stem: This is an implementation of the Snowball (or Porter II) Stemming Algorithm. It stems words to their root form (or stem) which greatly reduces the number of words that need to be compared when attributing semantic meaning, as all forms of the word are reduced down to a single form (e.g. 'dark', 'darker', and 'darkness' all stem to the word 'dark'). The contextual meaning of each word is preserved by combining the part of speech assigned in "text tag" and the semantic meaning derived in "text vector".

Text Vector:
