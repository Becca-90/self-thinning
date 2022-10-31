thinning_plot <- function(data, xvar, xlims = c(1e-02, 1), xlab ="mean stem diameter (m)", ylims =c(1E-2, 1E1), ylab = "density", title="") {
  
  data[["x"]] <- data[[xvar]] ##which column name for what we want to plot against density
  
  data %>% 
    filter(time > 0.01) %>%
    mutate(
      my_label = find_closest(round(time, 2), at = c(5)),
      diameter_stem_av_cm = diameter_stem_av*100, 
      density_m2=density*10000
    ) %>%
    ggplot(aes(x, density, col = trait_value, label=my_label)) + 
    geom_line() + 
    #geom_text_repel(arrow = arrow(length = unit(0.01, "npc")), box.padding = 0.01, max.overlaps = getOption("ggrepel.max.overlaps", default = 20)) +
    geom_text(aes(label=my_label), hjust=0, vjust=0) +
    scale_x_log10(limits=xlims, name=xlab, labels = scales::comma) +
    scale_y_log10(limits=ylims, name = "density" ~ (m^2), labels = scales::comma) +
    theme_classic(base_size = 18) +
    ggtitle(title)
}