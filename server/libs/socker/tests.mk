##
## EPITECH PROJECT, 2020
## Socker
## File description:
## testing rule
##

$(TARGET_TEST): CFLAGS	+=	--coverage -Wno-unused-parameter
$(TARGET_TEST): LDFLAGS	+=	-lcriterion -lgcov
$(TARGET_TEST): $(OBJ_TEST)
	$(CC) -o $(TARGET_TEST) $(OBJ_TEST) $(LDFLAGS)