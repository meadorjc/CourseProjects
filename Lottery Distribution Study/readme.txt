Caleb Meador 12/17/2013 - meadorjc at gmail.com
    
    Usage: lotteryMJ

    Program takes no arguments.

Random Lottery Number Distribution Study (GE1)
 - For detailed program specifications, see LotteryDistributionSpecifications.pdf

    Purpose: Generate 6 non-duplicate random numbers (0-9) and test for 
    frequency of Type-1 matches and Type-2 matches.

    Type-1 Match: Random numbers must match exactly by position and number.
        Randomly Generated Numbers    :    7, 2, 1, 9, 4, 5
        Type-1 Match                  :    7, 2, 1, 9, 4, 5

    Type-2 Match: Random numbers must match regardless of position.
        Randomly Generated Numbers    :     7, 2, 1, 9, 4, 5
        Type-2 Match                  :     2, 7, 1, 9, 4, 5
        Type-2 Match                  :     7, 2, 9, 1, 4, 5
        ...                           :     ...

    Program: Generate 10,000,000 sets of 6 non-duplicate random numbers
        and calculate the percentage of sets that result in Type-1 matches
        and Type-2 matches, displaying the percentages of each.
    