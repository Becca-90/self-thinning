grow_tidy_expand_totals <- function(oderel=1e-4, odeabs=1e-4, scheps=0.005, rec_decay=0, traits) {
  
  
  control = scm_base_control()
  
  control$ode_tol_rel <- oderel
  control$ode_tol_abs <- odeabs
  control$schedule_eps <- scheps
  
  p = base_params(rec_decay = rec_decay)
  patch <- run_mypatch_edit(p0 = p, ctrl = control, traits = traits)
  patch_tidy <- tidy_patch(patch)
  patch_expand <- FF16_expand_state(patch_tidy)
  
  patch_expand$species %>% 
  integrate_over_size_distribution() %>%
    mutate(
      area_stem_av = area_stem / individuals
      )
}
