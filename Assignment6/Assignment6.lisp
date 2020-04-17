;Suraj Ilavala
;CMSC 403: Assignment 6
;Due: April 7, 2020

;This is the common list function myList, it creates a list and returns (4 (7 22) "art" ("math" (8) 99) 100)
(defun myList()
    (list 4 (list 7 22) "art" (list "math" (list 8) 99) 100)
)

;will find the leap years between 1800 and 2020 recursively
(defun leapYear (&optional (curYear 1800) leapyears)
    ;loop continues until 2021 is reach
    (if (> curYear 2021) 
        ;returns list of leap years
        (RETURN-FROM leapYear leapyears) 
        ;checks the year by dividing it by 4 if it is will check to 
        ;   make sure the year is not divisible by 100, if so it will 
        ;   add it to the leap year but if it is not it will make a 
        ;   additional check by dividing the year by 400 if it is it 
        ;   will add it to the leapyear list
        (if (/= 0 (mod curYear 4)) 
            (leapYear (+ curYear 1) leapyears)
            (if (/= 0 (mod curYear 100)) 
                (leapYear (+ curYear 1) (append leapyears (list curYear)))
                (if (/= 0 (mod curYear 400)) 
                    (leapYear (+ curYear 1) leapyears)
                    (leapYear (+ curYear 1) (append leapyears (list curYear))) 
                )
            )
        )
    )
)

;union-
(defun union- (list1 list2 &optional combinedList)
    ;checks for null list
    (if (null list1)
        ;returns a list with all the elements this list does not contain duplicates
        (RETURN-FROM union- (append (reverse combinedList) list2))
        ;removes any duplicates and adds all elements to one combined list
        (union- (cdr list1) (remove (car list1) list2) (cons (car list1) combinedList)) 
    )
)

;avg
;returns the average of a list of numbers
(defun avg (aList)
    ;checks for existing list
    (when aList
        ;adds all numbers in list and then divides the total with the length of the list
        (/ (apply #'+ aList) (length aList)))
) ;39/5

;isType
;NOTE: return value of isType should be in the form given, but the exact return value will differ for each individual
(defun isType (isType)
    (lambda (value) (typep value isType))
)

;taxCalculator
(defun taxCalculator (limit rate value &optional list)
    ;recursion continues until value is null then it returns the complete list in order
    (if (null value) 
        (RETURN-FROM taxCalculator (reverse list)) 
    )
    ;checks value is less then limit it calculate the tax accordingly with the rate
	(if (< limit (car value)) 
		(taxCalculator limit rate (cdr value) (cons (* rate (car value)) list))
		(taxCalculator limit rate (cdr value) (cons (car value) list))
	)
)
;clean
;aFunc represents a function which takes a single argument. aFunc returns true if the given 
;argument is a number. aFunc is not a real function name, rather it is a stand in name for 
;either a system or user defined function which will be used instead.
(defun clean (aFunc aList)
    ;checks for a empty list if found then the all the nil will be cleaned
    (if (null aList) 
        (RETURN-FROM clean NIL)
    )
    ;makes sure there is still a list with elements
    (if (listp (car aList)) 
            ;appends the list after a aFunc function is cleaned
            (append (list (clean aFunc (car aList))) (clean aFunc (cdr aList))) 
            ; calls the function with the list and then appends and cleans 
            (if (funcall aFunc (car aList))
                (append (list (car aList)) (clean aFunc (cdr aList))) 
                (clean aFunc (cdr aList)) 
            )
        )
)

;threeWayBranch
(defmacro threeWayBranch (x y toExecute)
    (if (< x y);checks if x < y then the first element is printed
        (car (last (map 'list #'eval (first toExecute))))
    )
    (if (> x y);checks if x > y then the second element is printed
        (car (last (map 'list #'eval (second toExecute))))
    )
    (if (= x y);checks if x = y then the third element is printed
        (car (last (map 'list #'eval (third toExecute))))
    )
)
