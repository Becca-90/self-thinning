grow_tidy_expand_totals <- function(...) {
  
  patch <- run_mypatch(...)
  patch_tidy <- tidy_patch(patch$out)
  patch_expand <- FF16_expand_state(patch_tidy)
  
  max_height <- patch_expand$species %>%
    select(-.data$node) %>% stats::na.omit() %>%
    filter(.data$step > 1) %>% 
    group_by(.data$step, .data$time, .data$patch_density, .data$species) %>% 
    summarise(
      height_max = max(.data$height))
  
  patch_total <-
    patch_expand$species %>% 
    integrate_over_size_distribution() %>%
    mutate(
      # create average sizes
      across(c(diameter_stem, area_stem, area_leaf, height, mass_above_ground), ~.x/density, 
             .names = "{.col}_av")
    ) %>%
    cbind(max_height$height_max)
  
  list(p = patch$p, patch = patch, patch_expand = patch_expand, patch_total = patch_total)
}