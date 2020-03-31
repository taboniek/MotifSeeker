# MotifSeeker

### Algorithm reads two txt files:
1. First contains data with nucleotide sequences
2. Second with credibility assessment for each nucleotide from sequences above

User can choose how long "window" (long of substrings) can be from 4 to 7 nucleotides and what is the acceptable credibility. Nucleotides below this acceptable credibility will be considered as potential deletions points. For window size 4-5 maximum number of deletions=1, for size 6-7 two deletions.

Algorithm searches cliques in heuristic way - it looks for the longest match in at least 4 sequences. Then it searches next clique, which is neighbouring to previous one. It repeats as long as possible. **Founded result is the longest local match in given sequences.**
