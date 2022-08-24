grow_tidy_expand_totals <- function(schedule_eps=0.0005, B_lf1 = 0.8273474, B_lf2 = 0.5, ...) {
  
  control = scm_base_control()
  
  control$schedule_eps <- schedule_eps
  
  p <- base_params(...)
  patch <- run_mypatch(p0 = p, ctrl = control, B_lf1 = B_lf1, B_lf2 = B_lf2, d_I = d_I)
  patch_tidy <- tidy_patch(patch)
  patch_expand <- FF16_expand_state(patch_tidy)
  
  patch_total <-
    patch_expand$species %>% 
    integrate_over_size_distribution() %>%
    mutate(
      # create average sizes
      across(c(diameter_stem, area_stem, area_leaf, height, mass_above_ground), ~.x/density, 
             .names = "{.col}_av")
    )
  
  list(p = p, patch = patch, patch_expand = patch_expand, patch_total = patch_total)
}
