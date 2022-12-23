#include "../lib/Polynomial.h"

Node *createNode(Monome m)
{
    Node *node = (Node *)malloc(sizeof(Node));
    if (node != NULL)
    {
        node->monome = (Monome *)malloc(sizeof(Monome));
        if(node->monome == NULL) return NULL;
        node->monome->pow = m.pow;
        node->monome->coef = m.coef;
        node->next = NULL;
        node->prev = NULL;
    }
    return node;
}

void initPolynomial(Polynomial *poly)
{
    poly->head = NULL;
    poly->tail = NULL;
}

void removeNode(Polynomial *p, Node *node)
{
    if (p->head != p->tail)
    {
        if (node->next == NULL)
        {
            p->tail = node->prev;
            node->prev->next = NULL;
            node->prev = NULL;
        }
        else if (node->prev == NULL)
        {
            p->head = node->next;
            node->next->prev = NULL;
            node->next = NULL;
        }
        else
        {
            node->prev->next = node->next;
            node->next->prev = node->prev;
            node->prev = NULL;
            node->next = NULL;
        }
    }
    else
        initPolynomial(p);
    free(node);
}

void addNode(Node *node, Polynomial *poly)
{
    if (node != NULL && node->monome->coef != 0)
    {
        if (poly->head == NULL)
        {
            poly->head = node;
            poly->tail = node;
        }
        else
        {
            if (poly->tail->monome->pow > node->monome->pow)
            {
                poly->tail->next = node;
                node->prev = poly->tail;
                poly->tail = node;
            }
            else if (poly->tail->monome->pow == node->monome->pow)
            {
                poly->tail->monome->coef += node->monome->coef;
                if (poly->tail->monome->coef == 0)
                    removeNode(poly, poly->tail);
            }
            else if (poly->tail->monome->pow < node->monome->pow)
            {
                Node *tmp = poly->head;
                while (tmp != NULL)
                {
                    if (node->monome->pow > tmp->monome->pow)
                    {
                        node->next = tmp;
                        node->prev = tmp->prev;
                        tmp->prev = node;

                        if (poly->head == tmp)
                            poly->head = node;

                        break;
                    }
                    else if (node->monome->pow == tmp->monome->pow)
                    {
                        tmp->monome->coef += node->monome->coef;
                        if (tmp->monome->coef == 0)
                            removeNode(poly, tmp);
                        break;
                    }

                    tmp = tmp->next;
                }
                tmp = NULL;
                free(tmp);
            }
        }
    }
}

Polynomial scanPoly()
{
    Polynomial *poly = (Polynomial *)malloc(sizeof(Polynomial));
    Node *node;
    Monome monome;

    initPolynomial(poly);
    printf("Saisie  du polynome (Pour areter entrer une pruissance negative) : \n");
    do
    {
        monome = scanMonome();
        if (monome.pow >= 0)
        {
            node = createNode(monome);
            addNode(node, poly);
        }

    } while (monome.pow >= 0);

    return *poly;
}

void printPolynomial(Polynomial poly)
{
    if (poly.head == NULL)
        printf("%d", 0);
    while (poly.head != NULL)
    {
        printMonome(*(poly.head->monome));
        poly.head = poly.head->next;
        if (poly.head != NULL && poly.head->monome->coef > 0)
            printf("+");
    }
}

double calulate(Polynomial poly, double x)
{
    double result = 0;
    // Monome monome;
    while (poly.head != NULL)
    {
        // monome = *poly.head->monome;
        result += poly.head->monome->coef * pow(x, poly.head->monome->pow);
        poly.head = poly.head->next;
    }
    return result;
}

Polynomial sumPolynomial(Polynomial p, Polynomial q)
{
    Node *node;
    Polynomial sum;
    initPolynomial(&sum);
    while (q.head != NULL)
    {
        node = createNode(*q.head->monome);
        addNode(node, &sum);
        q.head = q.head->next;
    }
    while (p.head != NULL)
    {
        node = createNode(*p.head->monome);
        addNode(node, &sum);
        p.head = p.head->next;
    }
    return sum;
}

void changePolynomialSign(Polynomial *poly)
{
    Node *tmp = poly->head;
    while (tmp != NULL)
    {
        tmp->monome->coef *= -1;
        tmp = tmp->next;
    }
}

Polynomial substractPolynomial(Polynomial p, Polynomial q)
{
    changePolynomialSign(&q);
    return sumPolynomial(p, q);
}

boolean nodesAreEqual(Node a, Node b)
{
    return monomesAreEqual(*a.monome, *b.monome);
}

boolean comparePolynomial(Polynomial p, Polynomial q)
{
    if (nodesAreEqual(*p.head, *q.head))
    {
        while ((p.head != NULL) && (q.head != NULL))
        {
            if (!nodesAreEqual(*p.head, *q.head))
                return FALSE;

            p.head = p.head->next;
            q.head = q.head->next;
        }
        if ((p.head == NULL) && (q.head == NULL))
            return TRUE;
    }
    return FALSE;
}

Polynomial polynomialDerivative(Polynomial poly)
{
    Polynomial derivative;
    Monome dMonome;
    initPolynomial(&derivative);
    while (poly.head != NULL)
    {
        dMonome = monomeDerivative(*poly.head->monome);
        addNode(createNode(dMonome), &derivative);
        poly.head = poly.head->next;
    }
    return derivative;
}

/* char *polynomialToString(Polynomial poly)
{
    char *polyToString = (char *)malloc(POLY_MAX_SIZE * sizeof(char));
    sprintf(polyToString, "");
    while (poly.head != NULL)
    {
        strcat(polyToString, monomeToString(*poly.head->monome));
        poly.head = poly.head->next;
        if (poly.head != NULL && poly.head->monome->coef > 0)
            strcat(polyToString, "+");
    }
    return polyToString;
} */

Curve computePolynomial(Polynomial poly, int range[])
{
    Curve polyCurve;
    int i, j = 0;
    polyCurve = initCurve(range[1] - range[0], range);
    printf("inc\n");
    for (i = range[0]; i <= range[1]; i++)
    {
        polyCurve.points[j].x = (double)i;
        polyCurve.points[j].y = calulate(poly, (double)i);
        j++;
    }
    printf("Polynomials are computed!");
    return polyCurve;
}