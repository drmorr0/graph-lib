
set(graph_src 
	graph.cpp 
	graph_io.cpp 
	graph_layout.cpp 
	graph_order.cpp 
	graph_utils.cpp
)

add_library(graph SHARED ${graph_src})


