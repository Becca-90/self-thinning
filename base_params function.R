base_params <- function(rec_decay = 0) {
  
  p0 <- scm_base_parameters("FF16")
  
  p0$strategy_default$lma <- 0.07
  p0$strategy_default$hmat <- 15
  p0$strategy_default$rho <- 700
  p0$strategy_default$a_l1 <- 2.17
  p0$strategy_default$a_l2 <- 0.5
  
  p0$strategy_default$recruitment_decay <- rec_decay
  
  p0
}