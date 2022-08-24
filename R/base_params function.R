base_params <- function(rec_decay = 5, a_l1 = 2.17, a_l2 = 0.5, d_I = 0.1) {
  
  p0 <- scm_base_parameters("FF16")
  
  p0$strategy_default$recruitment_decay <- rec_decay  
  p0$strategy_default$a_l1 <- a_l1
  p0$strategy_default$a_l2 <- a_l2
  p0$strategy_default$d_I <- d_I
  
  p0
}
