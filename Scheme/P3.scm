#lang scheme

(define (reverse lst)
  (define (reverse-helper lst acc)
    (cond
      ((null? lst) acc)
      (else (reverse-helper (cdr lst) (cons (car lst) acc)))))

  (reverse-helper lst '()))

(display (reverse '(A B B C D D E F G G)))
