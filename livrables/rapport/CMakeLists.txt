find_program(LATEXMK_EXECUTABLE latexmk REQUIRED)

# --- Cible "rapp" : PDF dans le build, fichiers temporaires dans le build ---
set(PDF_BUILD "${CMAKE_CURRENT_BINARY_DIR}/rapport.pdf")
add_custom_command(
    OUTPUT "${PDF_BUILD}"
    COMMAND ${LATEXMK_EXECUTABLE} -pdf -interaction=nonstopmode
            -outdir="${CMAKE_CURRENT_BINARY_DIR}"
            "${CMAKE_CURRENT_SOURCE_DIR}/rapport.tex"
    DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/rapport.tex"
    COMMENT "Compilation rapport (sortie build)"
)
add_custom_target(rapp DEPENDS "${PDF_BUILD}")

# --- Cible "final-rapp" : PDF dans le source, fichiers temporaires dans le source ---
set(PDF_SRC "${CMAKE_CURRENT_SOURCE_DIR}/rapport.pdf")
add_custom_command(
    OUTPUT "${PDF_SRC}"
    COMMAND ${LATEXMK_EXECUTABLE} -pdf -interaction=nonstopmode
            -outdir="${CMAKE_CURRENT_SOURCE_DIR}"
            "${CMAKE_CURRENT_SOURCE_DIR}/rapport.tex"
    DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/rapport.tex"
    COMMENT "Compilation rapport (sortie source)"
)
add_custom_target(final-rapp DEPENDS "${PDF_SRC}")