base_params <- function(rec_decay = 0, lma = 0.1, rho=500, hmat=25) {
  
  p0 <- scm_base_parameters("FF16")
  
  p0$strategy_default$hmat <- 25
  p0$strategy_default$lma <-  lma
  p0$strategy_default$rho <-  rho
  p0$strategy_default$a_l1 <- 2.17
  p0$strategy_default$a_l2 <- 0.5
  
  p0$strategy_default$recruitment_decay <- rec_decay
  
  p0
}
