#lang scheme

(define (rotate lst)
  (define (rotate-once lst)
    (if (null? lst)
        '()
        (append (cdr lst) (list (car lst)))))
  
  (define (all-rotations lst n)
    (if (= n 0)
        '()
        (cons lst (all-rotations (rotate-once lst) (- n 1)))))
  (all-rotations lst (length lst))) 
  

(rotate '(a b c d e))