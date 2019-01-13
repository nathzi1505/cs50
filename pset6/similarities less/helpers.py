from nltk.tokenize import sent_tokenize


def substrings_ex(a, n):
    """Extracts set of substrings in string a"""
    sub_strings = set()
    length = len(a)  # Extracts the length of the string
    for i in range(length):
        if (i + n) >= (length + 1):  # If it approaches the end of the string
            break
        else:
            sub_strings.add(a[i:(i + n)])
    temp = list(sub_strings)
    return temp


def lines(a, b):
    """Return lines in both a and b"""
    match_lines = set()
    line_a = a.splitlines()
    line_b = b.splitlines()
    for sub_a in line_a:
        for sub_b in line_b:
            if (sub_a == sub_b):
                match_lines.add(sub_a)
    l_match_lines = list(match_lines)  # Converts the set into a list
    return l_match_lines


def sentences(a, b):
    """Return sentences in both a and b"""
    match_sentences = set()
    sent_sentences_a = sent_tokenize(a)
    sent_sentences_b = sent_tokenize(b)
    for sentence_a in sent_sentences_a:
        for sentence_b in sent_sentences_b:
            if (sentence_a == sentence_b):
                match_sentences.add(sentence_a)
    l_match_sentences = list(match_sentences)  # Converts the set into a list
    return l_match_sentences


def substrings(a, b, n):
    """Return substrings of length n in both a and b"""
    match_substrings = []
    substring_a = substrings_ex(a, n)
    substring_b = substrings_ex(b, n)
    for sub_a in substring_a:
        for sub_b in substring_b:
            if (sub_a == sub_b):
                match_substrings.append(sub_a)
    return match_substrings