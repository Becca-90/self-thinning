interpolate_stem_diam <- function(stem_diameter_av, density, xout=0.05, method="linear") {

  interpolations <- approx(stem_diameter_av, density, xout, method)
  
  totals <- tibble(diameter_stem_av = interpolations[["x"]], density = interpolations[["y"]]) %>% 
    mutate(
      step = NA, time = NA, patch_density = NA, species = NA, min_height = NA, height = NA, mortality = NA, fecundity = NA, area_heartwood = NA, mass_heartwood = NA, offspring_produced_survival_weighted = NA, 
      log_density = NA, area_leaf = NA, mass_leaf = NA, area_sapwood = NA, mass_sapwood = NA, area_bark = NA, mass_bark = NA, area_stem = NA, diameter_stem = NA, 
      mass_root = NA, mass_live = NA, mass_total = NA, mass_above_ground = NA, area_stem_av = NA, area_leaf_av = NA, height_av = NA, mass_above_ground_av = NA, my_label = NA
    )
  
}
