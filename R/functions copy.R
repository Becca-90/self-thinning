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


## add time labels to plots
find_closest <- function(x, at){
  
  out <- rep("", length(x))  
  
  for(a in at){
    dist <- abs(x-a)
    i <- which(dist == min(dist))
    out[i] <- a
  } 
  out
}

thinning_plot <- function(data, xvar, xlims,  xlab=xvar, ylims =c(1E-4, 1E0), title="") {
  
  data[["x"]] <- data[[xvar]] ##which column name for what we want to plot against density
  
  data %>% 
    filter(time > 0.1) %>%
    mutate(
      my_label = find_closest(round(time, 2), at = c(1.25, 2.5, 5, 10, 20, 40, 80))     
    ) %>%
    ggplot(aes(x, density, col=run, label=my_label)) + 
    geom_line() + 
    geom_text_repel(arrow = arrow(length = unit(0.01, "npc")), box.padding = 0.3, max.overlaps = getOption("ggrepel.max.overlaps", default = 20)) +
    #geom_text(nudge_x = 0, nudge_y = 0.1) +
    scale_x_log10(limits=xlims, name=xlab) +
    scale_y_log10(limits=ylims, name = "Density (/m2)") +
    theme_classic(base_size = 18) +
    ggtitle(title)
}

grow_tidy_expand_totals <- function(...) {
  
  patch <- run_mypatch(...)
  patch_tidy <- tidy_patch(patch$out)
  patch_expand <- FF16_expand_state(patch_tidy)
  
  patch_total <-
    patch_expand$species %>% 
    integrate_over_size_distribution() %>%
    mutate(
      # create average sizes
      across(c(diameter_stem, area_stem, area_leaf, height, mass_above_ground), ~.x/density, 
             .names = "{.col}_av")
    )
  
  list(p = patch$p, patch = patch, patch_expand = patch_expand, patch_total = patch_total)
}

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
# lma 0.07 = 2.699283, lma 0.125 = 1.001497, lma 0.24 = 0.32825
