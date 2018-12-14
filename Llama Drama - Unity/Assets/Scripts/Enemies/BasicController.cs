using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BasicController : PhysicsObject
{
    public float maxSpeed;
    public bool moveLeft = true;
    SpriteRenderer sr;

    // Use this for initialization
    void Start()
    {
        sr = GetComponent<SpriteRenderer>();
    }

    protected override void ComputeVelocity()
    {
        Vector2 move = Vector2.zero;

        if (moveLeft == true)
        {
            move.x = -1.0f;
        }
        else if (moveLeft == false)
        {
            move.x = 1.0f;
        }

        targetVelocity = move * maxSpeed;
    }

    private void OnCollisionEnter2D(Collision2D collision)
    {
        if (collision.gameObject.tag == "Barrier" || collision.gameObject.tag == "Enemy")
        {
            if (moveLeft)
            {
                moveLeft = false;
                sr.flipX = true;
            }
            else
            {
                moveLeft = true;
                sr.flipX = false;
            }

        }
    }
}
