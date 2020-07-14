1) 3d initialization (zero)    [done]
	--each cell in the grid will be a struct including obstacle
2) file(for nets)
3) open file and read nets
4) loop over nets to go net by net
	-- mark target and sources of net
	-- hana5d el z w n3mlo mod 2 w we will decide ver or horz
	-- bfs: numbering the grid w add to queue
		.. we will mark boolean matrix visited
		.. check the need for vias
	-- backtracing: we will mark obstacles as 1
		..uncheck visited nodes once arrived to target		

