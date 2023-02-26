grow_under_rain <- function(rainfall = 1, patch_life = 10) {
  
  ctrl = scm_base_control()
  ctrl$schedule_eps <- 0.005
  
  p0 = scm_base_parameters("FF16w")
  p0$strategy_default$recruitment_decay <- 5  
  p0$strategy_default$a_l1 <- 2.17
  p0$strategy_default$a_l2 <- 0.5
  p0$strategy_default$hmat <- 12
  p0$strategy_default$a_dG1 = 5.5
  p0$strategy_default$a_dG2 = 20
  p0$strategy_default$a_f1 <- 0
  p0$max_patch_lifetime = patch_life
  
  hyper_par_fn <- make_FF16_hyperpar(B_lf1 = 0.8273474, B_lf2 = 0.5, B_dI1 = 0, B_dI2 = 0, B_kl2 = 1.71, B_lf5 = 1, B_lf4 = 21000, B_ks2 = 0, latitude = 28.182)
  
  p1 <- expand_parameters(trait_matrix(c(0.1457419, 0.002381510, 606.8343, 0.000500000), c("lma", "narea", "rho", "omega")), p0, hyper_par_fn, mutant = FALSE, birth_rate_list = 200)
  env <- make_environment("FF16w", soil_initial_state = 0.5, rainfall = rainfall)
  
  results <- build_schedule(p1, ctrl = ctrl, env = env)
  out <- run_scm_collect(results, ctrl=ctrl, env = env)
  
  patch_tidy <- tidy_patch(out)
  patch_expand <- FF16_expand_state(patch_tidy)
  
  patch_total <-
    patch_expand$species %>% 
    integrate_over_size_distribution() %>%
    mutate(
      across(c(diameter_stem, area_stem, area_leaf, height, mass_above_ground), ~.x/density, 
             .names = "{.col}_av")
    )
  
  patch_total
  
}