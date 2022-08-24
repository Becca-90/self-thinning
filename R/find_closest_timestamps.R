find_closest <- function(x, at){
  
  out <- rep("", length(x))  
  
  for(a in at){
    dist <- abs(x-a)
    i <- which(dist == min(dist))
    out[i] <- a
  } 
  out
}