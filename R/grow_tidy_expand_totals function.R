grow_tidy_expand_totals <- function(oderel=1e-4, odeabs=1e-4, scheps=0.0005, rec_decay=5, ...) {
  
  control = scm_base_control()
  
  control$ode_tol_rel <- oderel
  control$ode_tol_abs <- odeabs
  control$schedule_eps <- scheps
  
  p <- base_params(rec_decay = rec_decay)
  patch <- run_mypatch_edit(p0 = p, ctrl = control, ...)
  patch_tidy <- tidy_patch(patch)
  patch_expand <- FF16_expand_state(patch_tidy)
  
  patch_total <- 
    patch_expand$species %>% 
    integrate_over_size_distribution() %>%
    mutate(
      diameter_stem = (2 * sqrt (area_stem / pi)),
      # create average sizes
      across(c(area_stem, diameter_stem, area_leaf, height, mass_above_ground), ~.x/individuals, 
      .names = "{.col}_av"),
    )
  
  list(p = p, patch = patch, patch_expand = patch_expand, patch_total = patch_total)
}
