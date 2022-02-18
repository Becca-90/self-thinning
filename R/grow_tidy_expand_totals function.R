grow_tidy_expand_totals <- function(oderel=1e-4, odeabs=1e-4, scheps=0.0001, rec_decay=5, traits=trait_matrix(0.625, "lma"), B_lf1 = 1, narea = 0.00187) {
  
  
  control = scm_base_control()
  
  control$ode_tol_rel <- oderel
  control$ode_tol_abs <- odeabs
  control$schedule_eps <- scheps
  
  p = base_params(rec_decay = rec_decay)
  patch <- run_mypatch_edit(p0 = p, ctrl = control, traits = traits, B_lf1 = B_lf1, narea = narea)
  patch_tidy <- tidy_patch(patch)
  patch_expand <- FF16_expand_state(patch_tidy)
  
  patch_total <- patch_expand$species %>% 
  integrate_over_size_distribution() %>%
    mutate(
      area_stem_av = area_stem / individuals,
      height_av = height / individuals,
      stem_diameter_av = (2 * sqrt (area_stem_av / pi)),
      mass_av = mass_total / individuals
      )
  
  list(p = p, patch = patch, patch_expand = patch_expand, patch_total = patch_total)
  
}
