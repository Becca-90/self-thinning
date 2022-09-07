base_params <- function(rec_decay = 5, a_l1 = 2.17, a_l2 = 0.5, hmat = 16, a_dG1 = 5.5, a_dG2 =20) {
  
  p0 <- scm_base_parameters("FF16")
  
  p0$strategy_default$recruitment_decay <- rec_decay  
  p0$strategy_default$a_l1 <- a_l1
  p0$strategy_default$a_l2 <- a_l2
  p0$strategy_default$hmat <- hmat
  p0$strategy_default$a_dG1 = a_dG1
  p0$strategy_default$a_dG2 = a_dG2

  p0
}


run_mypatch <- function (
  traits = trait_matrix(c(0.24), c("lma")),
  birth_rate = 200,
  latitude = 28.182,
  schedule_eps = 0.005,
  B_dI1 = 0,
  B_lf1 = 0.8273474, 
  B_lf2 = 0.5, ...) {

  ctrl = scm_base_control()
  
  ctrl$schedule_eps <- schedule_eps
  
  p0 = base_params(...)
  
  hyper_par_fn <- make_FF16_hyperpar(B_lf1 = B_lf1, B_lf2 = B_lf2, B_dI1 = B_dI1, latitude = latitude)
  
#  extra <- strategy_list(traits, p0, hyper_par_fn, birth_rate)
  
  p1 <- expand_parameters(traits, p0, hyper_par_fn, mutant = FALSE, birth_rate_list = birth_rate)

  results <- build_schedule(p1, ctrl = ctrl)
  out <- run_scm_collect(results, ctrl=ctrl)
  list(p = p1, out=out)
}

# k_l <- B_kl1 * (lma/lma_0)^(-B_kl2) = 0.4565855 * (lma/0.1978791)^(-1.71)