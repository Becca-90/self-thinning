run_mypatch <- function (
  traits = trait_matrix(c(0.24), c("lma")),
  birth_rate = 200,
  p0 = base_params(),
  ctrl = scm_base_control(),
  latitude = 28.182,
  B_lf1 = 0.8273474, 
  B_lf2 = 0.5) {
  
  hyper_par_fn <- make_FF16_hyperpar(B_lf1 = B_lf1, B_lf2 = B_lf2, latitude = latitude)
  
  p1 <- expand_parameters(traits, p0, hyper_par_fn, mutant = FALSE)
  p1$birth_rate = birth_rate
  results <- build_schedule(p1, ctrl = ctrl)
  out <- run_scm_collect(results, ctrl=ctrl)

  out
}

# k_l <- B_kl1 * (lma/lma_0)^(-B_kl2) = 0.4565855 * (lma/0.1978791)^(-1.71)
# lma 0.07 = 2.699283, lma 0.125 = 1.001497, lma 0.24 = 0.32825