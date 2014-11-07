## Changelog

### Beta 0.2 (master) (November 14, 2014)

- `Added` : Function **lg\_gte\_apperture** as mono-threaded front-end to **lg\_gte\_apperturep** function
- `Added` : Function **lg\_gte\_apperturep** that invert processed induced by **lg\_etg\_apperturep** function
- `Added` : Function **lg\_etg\_apperture** as mono-threaded front-end to **lg\_etg\_apperturep** function
- `Added` : Function **lg\_etg\_apperturep** as parallelized gnomonic projections based on apperture angle and entire equirectangular mappings function
- `Added` : Function **lg\_gtt\_center** as mono-threaded front-end to **lg\_gtt\_centerp** function
- `Added` : Function **lg\_gtt\_centerp** as front-end to **lg\_gtt\_genericp** function that invert the process induced by **lg\_ttg\_centerp**
- `Added` : Function **lg\_gtt\_elphel** as mono-threaded front-end to **lg\_gtt\_elphelp** function
- `Added` : Function **lg\_gtt\_elphelp** as front-end to **lg\_gtt\_genericp** function that invert the process induced by **lg\_ttg\_elphelp**
- `Added` : Function **lg\_gtt\_generic** as mono-threaded front-end to **lg\_gtt\_genericp** function
- `Added` : Function **lg\_gtt\_genericp** as parallelized fundamental invert gnomonic projection function from rectilinear tile
- `Added` : Function **lg\_ttg\_center** as mono-threaded front-end to **lg\_ttg\_centerp** function
- `Added` : Function **lg\_ttg\_centerp** as front-end to **lg\_ttg\_genericp** function to simplify rectilinear-centered projections
- `Added` : Function **lg\_ttg\_elphel** as mono-threaded front-end to **lg\_ttg\_elphelp** function
- `Added` : Function **lg\_ttg\_elphelp** as front-end to **lg\_ttg\_genericp** function to simplify projections of images coming from Elphel camera devices
- `Added` : Function **lg\_ttg\_generic** as mono-threaded front-end to **lg\_ttg\_genericp** function
- `Added` : Function **lg\_ttg\_genericp** as parallelized fundamental gnomonic projection function from equirectangular tile
- `Revised` : Function **lg\_transform\_rotate** as mono-threaded front-end to **lg\_transform\_rotatep**
- `Added` : Function **lg\_transform\_rotatep** as parallelized equirectangular mappings rotation function
- `Revised` : Library name prefixes
- `Removed` : Function **gnomonic\_etg** for x,y-ratio discrepency
- `Removed` : Function **gnomonic\_gte_blend** replaced by better alpha-channel management in implemented functions
- `Removed` : Function **gnomonic\_gte** for x,y-ratio discrepency
- `Removed` : Function **gnomonic\_ttg** for x,y-ratio discrepency
- `Removed` : Module **gnomonic-coord** for coordinate conversion implying **gnomonic\_ttg\_coord** and **gnomonic\_gtt\_coord** functions removal for lack of utility

### Release 0.1 (July 29, 2014)

- `Added` : Initial release
