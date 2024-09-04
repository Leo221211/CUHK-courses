#!/bin/zsh

# Get today's date in seconds since the Unix epoch
today=$(date +%s)

# Get the year of May 3rd
year=$(date +%Y)

# Check if May 3rd of the current year has already passed
may3=$(date -j -f "%Y-%m-%d" "${year}-05-03" +%s)
if [ $may3 -lt $today ]; then
  # May 3rd of current year has already passed, get May 3rd of next year
  year=$(($year + 1))
  may3=$(date -j -f "%Y-%m-%d" "${year}-05-03" +%s)
fi

# Calculate the difference in days between today and May 3rd
diff=$((($may3 - $today) / 86400))

# Output the result
echo "There are $diff days until May 3."
