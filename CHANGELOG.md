## Changelog

### Release 0.2.1 (November 12, 2014)

- `Fixed` : Alpha-channel management issue in **lg\_gtt\_genericp** function

### Release 0.2 (November 11, 2014)

`Added` : **lg\_gte\_apperture** function as mono-threaded front-end to **lg\_gte\_apperturep**
`Added` : **lg\_gte\_apperturep** function that invert processed induced by **lg\_etg\_apperturep**
`Added` : **lg\_etg\_apperture** function as mono-threaded front-end to **lg\_etg\_apperturep**
`Added` : **lg\_etg\_apperturep** function as parallelized gnomonic projections
`Added` : **lg\_gtt\_center** function as mono-threaded front-end to **lg\_gtt\_centerp**
`Added` : **lg\_gtt\_centerp** function as front-end to **lg\_gtt\_genericp** inverting **lg\_ttg\_centerp**
`Added` : **lg\_gtt\_elphel** function as mono-threaded front-end to **lg\_gtt\_elphelp**
`Added` : **lg\_gtt\_elphelp** function as front-end to **lg\_gtt\_genericp** inverting **lg\_ttg\_elphelp**
`Added` : **lg\_gtt\_generic** function as mono-threaded front-end to **lg\_gtt\_genericp**
`Added` : **lg\_gtt\_genericp** function as parallelized invert gnomonic projection
`Added` : **lg\_ttg\_center** function as mono-threaded front-end to **lg\_ttg\_centerp**
`Added` : **lg\_ttg\_centerp** function as front-end to **lg\_ttg\_genericp** simplifying centered projections
`Added` : **lg\_ttg\_elphel** function as mono-threaded front-end to **lg\_ttg\_elphelp**
`Added` : **lg\_ttg\_elphelp** function as front-end to **lg\_ttg\_genericp**
`Added` : **lg\_ttg\_generic** function as mono-threaded front-end to **lg\_ttg\_genericp**
`Added` : **lg\_ttg\_genericp** function as parallelized gnomonic projection function
`Revised` : **lg\_transform\_rotate** function as mono-threaded front-end to **lg\_transform\_rotatep**
`Added` : **lg\_transform\_rotatep** function as parallelized equirectangular mappings rotation
`Revised` : Bitmap management to take into account padding bytes for (width)[4]≠0 images
`Revised` : Library name prefixes
`Removed` : **gnomonic\_etg** function for x,y-ratio discrepency
`Removed` : **gnomonic\_gte_blend** function replaced by better alpha-channel management
`Removed` : **gnomonic\_gte** function for x,y-ratio discrepency
`Removed` : **gnomonic\_ttg** function for x,y-ratio discrepency
`Removed` : Module **gnomonic-coord** for coordinate conversion

### Release 0.1 (July 29, 2014)

- `Added` : Initial release
