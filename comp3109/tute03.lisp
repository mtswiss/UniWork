(defun derive-num (num var)
0)

(defun derive-sym (symbol var)
(if (eq sym var) 1 0 ))

(defun derive-add (expr1 expr2 var)
(list '+ (derive expr1 var) (derive expr2 var))

(defun derive-minus (expr1 expr2 var)
(list '- (derive expr1 var) (derive expr2 var))

(defun derive-mult (expr1 expr2 var)
(list '+ 
	(list '* expr1 (derive expr2 var))
	(list '* expr2 (derive expr1 var))
))

(defun derive-divide (expr1 expr2 var)
(list '/
	(list '- 
		(list ( '* expr2 (derive expr1 var))
		(list ( '* expr1 (derive expr2 var))
	)
	(list 'square( expr2 ') )
))


(defun derive (exrp var)
(cond
((numberp expr) (derive-num expr var))
((symbolp expr)	(derive-sym expr var))
((eq (car exp) '+)
	(derive-add (nth 1 expr) (nth 2 expr) var))
((eq (car expr) '-)
	(derive-minus (nth 1 expr) (nth 2 expr) var))
((eq (car expr) '*)
	(derive-mult (nth 1 expr) (nth 2 expr) var))
((eq (car expr) '/)
	(derive-divide (nth 1 expr) (nth 2 expr) var))
(t (list 'derive expr var))
))

