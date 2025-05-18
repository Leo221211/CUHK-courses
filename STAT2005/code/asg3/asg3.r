# Q1
questionnaire <- function() {
  # create data frame
  data <- matrix(NA, nrow = 0, ncol = 3)
  colnames(data) = c("Name", "Age", "Gender")
  data <- as.data.frame(data)
  
  # ask questions
  cat("Please respond to the following three questions.\n\n")
  round <- 1
  repeat {
    # qustion 1
    cat("Question 1: What's your name? : ")
    data[round,1] <- readline()
    
    # question 2
    repeat {
      cat("Question 2: What's your age? <positive integer required>: ")
      inp <- readline()
      inp <- suppressWarnings(as.numeric(inp))
      if (is.na(inp) == TRUE) {
        cat("Please input positive integer.\n")
        next
      }
      if ((trunc(inp) != inp)|(inp <= 0)) {	
        cat("Please input positive integer.\n")
        next
      }
      data[round,2] <- inp
      break
    }
    
    # question 3
    repeat {
      cat("Question 3: What's your gender? <M/F>: ")
      inp <- toupper(readline())
      if ((inp == "M")|(inp == "F")) {
        data[round,3] <- inp
        break
      } else {
        cat("Please input M or F.\n")
      }
    }
    
    # ask new
    repeat {
      cat("New entry? <Y/N>: ")
      inp <- toupper(readline())
      if ((inp == "Y")|(inp == "N")) {
        break
      } else {
        cat("Please input Y or N.\n")
      }
    }
    if (inp == "Y") {
      round <- round+1
      next
    } else {
      break
    }
  }
  
  # output
  cat("The average age is", mean(data$Age),"from", round, "respondents.\n")
  num_male <- sum(data$Gender == "M")
  pie(c(num_male/round,1-num_male/round), init.angle = 90, labels = c("M", "F"))
  return(data)
}

data <- questionnaire()


# Q2
## a
T <- matrix(c(0.5, 0.3, 0.4, 
              0.2, 0.4, 0.3, 
              0.3, 0.3, 0.3), nrow = 3)

T %*% T

# Q2b
T6 <- diag(3)
for (i in 1:6) {
  T6 <- T6 %*% T
}
T6[1,1]

# Q2c
T_S1 <- matrix(c(0.45, 0.3, 0.4, 
                 0.25, 0.4, 0.3, 
                 0.3, 0.3, 0.3), nrow=3)
eig1<-eigen(t(T_S1))
(eig1$vectors[,1]/sum(eig1$vectors[,1]))[2] # 0.3117647

# Strategy 2
T_S2 <- matrix(c(0.5, 0.3, 0.4, 
                 0.2, 0.4, 0.35, 
                 0.3, 0.3, 0.25), nrow=3)
eig2<-eigen(t(T_S2))
(eig2$vectors[,1]/sum(eig2$vectors[,1]))[2] # 0.3035714

# since 0.3117647 > 0.3035714, so it is better to use strategy 1

###
