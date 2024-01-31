module astar_module 
    implicit none
    type :: Node
        integer :: id
        integer :: n_neighbours
        integer, allocatable :: neighbours(:)
        integer, allocatable :: costs(:)

        real :: g
        real :: h
        type(Node), pointer :: parent
    end type Node


    type :: Graph_t
        integer :: n_nodes
        type(Node), allocatable :: nodes(:)
    end type Graph_t

    contains

    function AStar(graph, start, goal) result(path)
        type(Graph_t), target :: graph
        integer :: start, goal
        type(Node), allocatable :: path(:), path_tmp(:)

        type(Node), pointer :: n
        integer :: current
        type(Node), allocatable, target :: openList(:), closedList(:)
        integer :: k, j, n_open, n_closed, lowestF, f, cost
        logical :: inOpenList, inClosedList, b


        allocate(openList(graph%n_nodes))
        allocate(closedList(graph%n_nodes))

        current = start
        graph%nodes(current)%g = 0
        
        n_open = 1
        n_closed = 0
        openList(1) = graph%nodes(current)

        do while (n_open > 0)
            ! Find the node with the lowest f value
            lowestF = 99999999
            do k = 1, n_open
                f = openList(k)%g + openList(k)%h
                if (f < lowestF) then
                    lowestF = f
                    current = openList(k)%id
                end if
            end do

            print *, "current: ", current

            ! remove current from open
            b = .false.
            do k = 1, n_open
                if (openList(k)%id == graph%nodes(current)%id) then
                    b = .true.
                end if
                if (b) then
                    openList(k) = openList(k+1)
                end if 
            end do
            n_open = n_open - 1

            ! add current to closed
            n_closed = n_closed + 1
            closedList(n_closed) = graph%nodes(current)

            ! check if goal
            if (graph%nodes(current)%id == goal) then
                exit
            end if

            ! for each neighbour of current
            do k = 1, graph%nodes(current)%n_neighbours
                cost = graph%nodes(current)%costs(k)

                ! if neighbour is in closed
                inClosedList = .false.
                do j = 1, n_closed
                    if (graph%nodes(current)%neighbours(k) == closedList(j)%id) then
                        inClosedList = .true.
                        exit
                    end if
                end do

                if (inClosedList) then
                    cycle
                end if

                ! if new path to neighbor is shorter
                if (graph%nodes(current)%g + cost < graph%nodes(graph%nodes(current)%neighbours(k))%g) then
                    graph%nodes(graph%nodes(current)%neighbours(k))%g = graph%nodes(current)%g + cost
                    graph%nodes(graph%nodes(current)%neighbours(k))%parent => graph%nodes(current)
                end if

                ! if neighbour is not in open
                inOpenList = .false.
                do j = 1, n_open
                    if (graph%nodes(graph%nodes(current)%neighbours(k))%id == openList(j)%id) then
                        inOpenList = .true.
                        exit
                    end if
                end do

                if (.not. inOpenList) then
                    graph%nodes(graph%nodes(current)%neighbours(k))%parent => graph%nodes(current)
                    n_open = n_open + 1
                    openList(n_open) = graph%nodes(graph%nodes(current)%neighbours(k))
                end if
            end do
        end do

        ! build path
        k = 0
        allocate(path_tmp(graph%n_nodes))
        n => graph%nodes(goal)
        do while (associated(n%parent))
            k = k + 1
            path_tmp(k) = n
            n => n%parent
        end do
        k = k + 1
        path_tmp(k) = n
            
        ! reverse path
        allocate(path(k))
        do j = 1, k
            path(j) = path_tmp(k-j+1)
        end do

        deallocate(path_tmp)
        deallocate(openList)
        deallocate(closedList)
    end function AStar
end module astar_module

program main
    use astar_module
    implicit none


    type(Graph_t) :: graph
    type(Node), allocatable :: path(:)
    integer :: i

    
    ! Create the graph
    graph%n_nodes = 8
    allocate(graph%nodes(graph%n_nodes))

    graph%nodes(1)%id = 1
    graph%nodes(1)%n_neighbours = 3
    allocate(graph%nodes(1)%neighbours(graph%nodes(1)%n_neighbours))
    allocate(graph%nodes(1)%costs(graph%nodes(1)%n_neighbours))
    graph%nodes(1)%neighbours = [2, 3, 4]
    graph%nodes(1)%h = 9
    graph%nodes(1)%costs = [2, 3, 10]

    graph%nodes(2)%id = 2
    graph%nodes(2)%n_neighbours = 2
    allocate(graph%nodes(2)%neighbours(graph%nodes(2)%n_neighbours))
    allocate(graph%nodes(2)%costs(graph%nodes(2)%n_neighbours))
    graph%nodes(2)%neighbours = [1, 5]
    graph%nodes(2)%h = 3
    graph%nodes(2)%costs = [2, 8]

    graph%nodes(3)%id = 3
    graph%nodes(3)%n_neighbours = 3
    allocate(graph%nodes(3)%neighbours(graph%nodes(3)%n_neighbours))
    allocate(graph%nodes(3)%costs(graph%nodes(3)%n_neighbours))
    graph%nodes(3)%neighbours = [1, 4, 7]
    graph%nodes(3)%h = 5
    graph%nodes(3)%costs = [10, 2, 2]

    graph%nodes(4)%id = 4
    graph%nodes(4)%n_neighbours = 3
    allocate(graph%nodes(4)%neighbours(graph%nodes(4)%n_neighbours))
    allocate(graph%nodes(4)%costs(graph%nodes(4)%n_neighbours))
    graph%nodes(4)%neighbours = [1, 3, 6]
    graph%nodes(4)%h = 6
    graph%nodes(4)%costs = [3, 2, 4]

    graph%nodes(5)%id = 5
    graph%nodes(5)%n_neighbours = 3
    allocate(graph%nodes(5)%neighbours(graph%nodes(5)%n_neighbours))
    allocate(graph%nodes(5)%costs(graph%nodes(5)%n_neighbours))
    graph%nodes(5)%neighbours = [2, 6, 8]
    graph%nodes(5)%h = 8
    graph%nodes(5)%costs = [8, 5, 10]

    graph%nodes(6)%id = 6
    graph%nodes(6)%n_neighbours = 3
    allocate(graph%nodes(6)%neighbours(graph%nodes(6)%n_neighbours))
    allocate(graph%nodes(6)%costs(graph%nodes(6)%n_neighbours))
    graph%nodes(6)%neighbours = [4, 5, 7]
    graph%nodes(6)%h = 4
    graph%nodes(6)%costs = [4, 5, 5]

    graph%nodes(7)%id = 7
    graph%nodes(7)%n_neighbours = 3
    allocate(graph%nodes(7)%neighbours(graph%nodes(7)%n_neighbours))
    allocate(graph%nodes(7)%costs(graph%nodes(7)%n_neighbours))
    graph%nodes(7)%neighbours = [3, 6, 8]
    graph%nodes(7)%h = 2
    graph%nodes(7)%costs = [2, 5, 1]

    graph%nodes(8)%id = 8
    graph%nodes(8)%n_neighbours = 2
    allocate(graph%nodes(8)%neighbours(graph%nodes(8)%n_neighbours))
    allocate(graph%nodes(8)%costs(graph%nodes(8)%n_neighbours))
    graph%nodes(8)%neighbours = [5, 7]
    graph%nodes(8)%h = 0
    graph%nodes(8)%costs = [10, 1]

    do i = 1, graph%n_nodes
        allocate(graph%nodes(i)%parent)
        graph%nodes(i)%parent => null()
        graph%nodes(i)%g = 99999999
    end do

    ! Find the path
    path = AStar(graph, 1, 8)

    ! Print the path
    do i = 1, size(path)
        print *, path(i)%id
    end do

end program main


