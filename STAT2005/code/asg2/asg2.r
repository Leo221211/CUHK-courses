
# Q1a
par(mfrow=c(1, 1))
plot(pressure$temperature,pressure$pressure)
curve((0.168 + 0.007*x)^(20/3), from = 0, to = 400, add = TRUE)

# Q1b
par(mfrow=c(1, 1))
plot(pressure$temperature,(pressure$pressure)^(3/20))
# The linear relationship is evident now
abline(0.168,0.007)

# Q1c
title(main="Plot of pressure^(3/20) against temperature")

# Q1d
par(mfrow=c(1,2))
plot(pressure$temperature,pressure$pressure, bty='n', las=1)
curve((0.168 + 0.007*x)^(20/3), from = 0, to = 400, add = TRUE)
plot(pressure$temperature,(pressure$pressure)^(3/20), bty='n', las=1)
abline(0.168,0.007)


# Q2
alt_matrix = function(n) {
  (row(matrix(0, n, n)) + col(matrix(0, n, n))) %% 2
}
alt_matrix(7)


# Q3
par(mfrow=c(1, 1))
plot(0, 0, type="n", xlim=c(0, 10), ylim=c(0, 10), bty="n", xlab="", ylab="")

line_lens = c(10, rep(seq(10, 1), each=2))
start = c(0, 0)
config = data.frame(
    colors = c("red", "orange", "green", "blue"),    # colors of Bottom, right, up, left
    directions = I(list(c(1, 0), c(0, 1), c(-1,0), c(0, -1)))  # direction of the growing line
    )

for (i in seq_along(line_lens)){
    # get config
    len = line_lens[i]
    color = config$colors[(i-1) %% 4 + 1]
    dir = config$directions[[(i-1) %% 4 + 1]]
    # print(paste(len, color, dir))
    # print(dir)
    
    # draw
    end = start + len * dir
    print(paste("Start:", toString(start), "End:", toString(end)))
    segments(x0=start[1], y0=start[2], x1=end[1], y1=end[2], col=color)
    
    # update
    start = end
}


#Q4
is_prime = function(n) {
    if (n <= 1) {
      return(FALSE)
    }
    if (n == 2) {
      return (TRUE)
    }
    for (i in 2:sqrt(n)) {
      if (n %% i == 0) {
        return(FALSE)
      }
    }
    return(TRUE)
}

primes = c()

for (i in seq(1:1000-3)) {
  if (is_prime(i) && is_prime(i+2)) {
    primes = c(primes, i, i+2)
  }
}

unique(primes)


# mqy

