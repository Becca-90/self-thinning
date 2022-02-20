run_mypatch_edit <- function(
  traits =  trait_matrix(c(0.24), c("lma")),
  birth_rate = 200,
  p0 = base_params(),
  ctrl=scm_base_control(),
  latitude = 28.182,
  ...
) {
  
  hyper_par_fn = make_FF16_hyperpar(...)
  
  p1 <- expand_parameters(traits, p0, hyper_par_fn, mutant = FALSE)
  p1$birth_rate = birth_rate
  results <- build_schedule(p1, ctrl = ctrl)
  out <- run_scm_collect(results, ctrl=ctrl)

  out
}
