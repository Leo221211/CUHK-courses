# Sample R code to test if the R environment is working

# Load necessary libraries
library(ggplot2)
library(dplyr)

# Create a sample data frame
data <- data.frame(
    x = rnorm(100),
    y = rnorm(100)
)

# Use dplyr to manipulate data
data <- data %>%
    mutate(z = x + y)

# Use ggplot2 to create a scatter plot
plot <- ggplot(data, aes(x = x, y = y)) +
    geom_point() +
    ggtitle("Scatter Plot of x and y")

# Print the plot
print(plot)
