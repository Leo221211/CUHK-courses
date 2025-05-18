# Q1
# a
seq(10, 30, by=2)

#b
1:25-rep(seq(0,16, by=4), rep(5,5))



# Q2
# a
roots <- polyroot(0:5)

# b
mode(roots)
# the answer is complex

# c
roots[order(Im(roots))]



# Q3
deck <- data.frame(
  suit = rep(c("D","C","H","S"), 13), 
  # D = ♦ Diamond, C = ♣ Club, H = ♥ Heart, S = ♠ Spade 
  rank = rep(2:14, 4) 
  # 11 = Jack, 12 = Queen, 13 = King, 14 = Ace ) 
)

# a
# Deck is a dataframe, and it has 52 rows and 2 columns, ie 52 observations and 2 variables.
# Each row contains the information of a playing card 
# (52 in total, with suit and rank recorded in corresponding column).
# The columns contains the information of the suit and rank of the card. 
# The first column is the suit of card and the second column is the rank of card in the row.

# b
hand <- deck[sample(52, size = 5, replace=F),]

# c
is.flush <- length(unique(hand$suit)) == 1
# verify:
# > hand <-deck[c(17, 9, 1, 49, 41), ]
# > is.flush <- length(unique(hand$suit)) == 1
# > is.flush
# [1] TRUE

# d
is.straight <- all(diff(sort(hand$rank)) == 1)|| all(sort(hand$rank) == c(2,3,4,5,14))
# verify
# > hand <-deck[5:9, ]
# > is.straight <- all(diff(sort(hand$rank)) == 1)|| all(sort(hand$rank) == c(2,3,4,5,14))
# > is.straight
# [1] TRUE

# e
is.straightflush <- is.flush & is.straight
is.flush <- is.flush & !is.straightflush
is.straight <- is.straight & !is.straightflush
# verify:
# > is.flush <- length(unique(hand$suit)) == 1
# > is.flush
# [1] TRUE
# > is.straight <- all(diff(sort(hand$rank)) == 1)|| all(sort(hand$rank) == c(2,3,4,5,14))
# > is.straight
# [1] TRUE
# > is.straightflush <- is.flush & is.straight
# > is.flush <- is.flush & !is.straightflush
# > is.straight <- is.straight & !is.straightflush
# > is.straightflush
# [1] TRUE
# > is.flush
# [1] FALSE
# > is.straight 
# [1] FALSE


# Q4
# a
moves <- data.frame(die_1 = sample(1:6, 100, replace = TRUE), 
                    die_2 = sample(1:6, 100, replace = TRUE))

# b
moves$step <- moves$die_1 + moves$die_2
moves$total_step <- cumsum(moves$step)
moves$round <- moves$total_step %/% 40
moves$side <- (moves$total_step %/% 10) %% 4
moves$land <- moves$total_step %% 10

# c
park_place <- sum(moves$side == 3 & moves$land == 7) > 0
boardwalk <- sum(moves$side == 3 & moves$land == 9) > 0
landed_on_both <- park_place & boardwalk



