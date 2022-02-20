base_params <- function(rec_decay = 0) {
  
  p0 <- scm_base_parameters("FF16")
  
  p0$strategy_default$a_l1 <- 3
  p0$strategy_default$a_l2 <- 0.5
  
  p0$strategy_default$recruitment_decay <- rec_decay
  
  p0
}
