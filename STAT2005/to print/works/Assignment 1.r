# Q1a
seq(10, 30, by=2)

# Q1b
1:25-rep(seq(0,16, by=4), rep(5,5))


# Q2a
roots <- polyroot(0:5)

# Q2b
mode(roots)

# Q2c
roots[order(Im(roots))]


# Q3
deck <- data.frame(
	suit = rep(c("D","C","H","S"), 13),
	# D = ♦ Diamond, C = ♣ Club, H = ♥ Heart, S = ♠ Spade
	rank = rep(2:14, 4)
	# 11 = Jack, 12 = Queen, 13 = King, 14 = Ace
)



# Q3a
# deck is a data frame with 52 observations and 2 variables
# each row represent a playing card
# the first column is the suit of card
# the second column is the rank of card

# Q3b
hand <- deck[sample(52, size = 5, replace=F),]
# hand <- deck[1:5,] # straight 2,3,4,5,6
# hand <- deck[c(1:4, 13),] # straight A,2,3,4,5
# hand <- deck[c(17,9,1,49,41),] # flush 
# hand <- deck[c(6,46,34,22,10),] # straight flush

# Q3c
is.flush <- length(unique(hand$suit)) == 1

# Q3d
min_rank <- min(hand$rank)
is.straight <- all(sort(hand$rank) == seq(min_rank, min_rank+4))|all(sort(hand$rank) == c(2,3,4,5,14))

# Q3e
(is.straightflush <- is.flush & is.straight)
(is.flush <- is.flush & !is.straightflush)
(is.straight <- is.straight & !is.straightflush)


# Q4a
moves <- data.frame(
	die_1 = sample(1:6, size=100, replace=T),
	die_2 = sample(1:6, size=100, replace=T)
)

# Q4b
moves$step <- with(moves, die_1+die_2)
moves$total_step <- cumsum(moves$step)
moves$round <- moves$total_step %/% 40
moves$side <- (moves$total_step %% 40) %/% 10
moves$land <- moves$total_step %% 10

# Q4c
PARK_PLACE = any((moves$side == 3) & (moves$land == 7)) 
BOARDWALK = any((moves$side == 3) & (moves$land == 9))
PARK_PLACE & BOARDWALK

