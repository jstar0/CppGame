#include<iostream>
#include"card.h"
#include"console.h"
#include"enemy.h"

extern int cardPrintX,cardPrintY;

void print(Card card)
{
    setcolor(card);
    print(card.description,cardPrintX,cardPrintY);
}
void Card::effect()
{
    
}
void AttackCard::effect(Enemy enemy)
{
    
}