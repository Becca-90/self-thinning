thinning_plot <- function(data, xvar, xlims = c(1e-02, 1e01), xlab=xvar, ylims =c(1E-4, 1E0), ylab = "density", title="") {
  
  data[["x"]] <- data[[xvar]] ##which column name for what we want to plot against density
  
  data %>% 
    filter(time > 0.1) %>%
    mutate(
      my_label = find_closest(round(time, 2), at = c(1.25, 2.5, 5, 10, 20, 40, 80))     
    ) %>%
    ggplot(aes(x, density, col = run, label=my_label)) + 
    geom_line() + 
    geom_text_repel(arrow = arrow(length = unit(0.01, "npc")), box.padding = 0.3, max.overlaps = getOption("ggrepel.max.overlaps", default = 20)) +
    #geom_text(nudge_x = 0, nudge_y = 0.1) +
    scale_x_log10(limits=xlims, name=xlab) +
    scale_y_log10(limits=ylims, name = "Density (/m2)") +
    theme_classic(base_size = 18) +
    ggtitle(title)
}