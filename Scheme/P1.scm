#lang scheme

(define (filter pred list)
  (cond
    ((null? list) '())
    ((pred (car list))
     (cons (car list) (filter pred (cdr list))))
  (else (filter pred (cdr list)))))

(filter (lambda (x) (< x 5)) '(3 9 5 8 2 4 7))