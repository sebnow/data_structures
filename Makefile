STRUCTURES=queue

all:
	@for structure in $(STRUCTURES); do $(MAKE) -C $$structure; done

clean:
	@for structure in $(STRUCTURES); do $(MAKE) -C $$structure clean; done
