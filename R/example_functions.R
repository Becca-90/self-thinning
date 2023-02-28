square <- function(data, power) {
  data^power
}

mean <- function(data) {
  sum(data)/length(data)
}


std_error <- function(data) {
  sd(data)/sqrt(length(data))
}


how_many <- function(vector, integer) {
  j <- 0
  for (i in 1:length(vector)) {
    if (vector[i] == integer) {
      j <- j+1
      i <- i+1
    }
  }
  j
}