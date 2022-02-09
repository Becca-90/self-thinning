grow_plot <- function(scheps=0.0001, rec_decay=5, traits=trait_matrix(0.625, "lma"), B_lf1 = 1, narea = 0.00187) {
  
  
  ctrl = scm_base_control()
  ctrl$schedule_eps <- scheps
  
  p = base_params(rec_decay = rec_decay)
  patch <- run_mypatch_edit(p0 = p, ctrl = ctrl, traits = traits, B_lf1 = B_lf1, narea = narea)
  patch_tidy <- tidy_patch(patch)
  patch_tidy_nona <- patch_tidy$species %>%
    drop_na()
  
  plot_size_distribution(patch_tidy_nona)
}
