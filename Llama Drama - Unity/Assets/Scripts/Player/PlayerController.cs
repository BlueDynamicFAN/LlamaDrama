using UnityEngine;

public class PlayerController : PhysicsObject
{
    public float jumpStrength;
    public float maxSpeed;

    protected override void ComputeVelocity()
    {
        Vector2 move = Vector2.zero;

        move.x = Input.GetAxis("Horizontal");

        if (Input.GetButtonDown("Jump") && grounded)
        {
            velocity.y = jumpStrength;
        }

        if (!grounded)
        {
            targetVelocity = move * (maxSpeed * 0.8f);
        }
        else if (grounded)
        {
            targetVelocity = move * maxSpeed;
        }
    }

    private void OnTriggerStay2D(Collider2D collision)
    {
        if (collision.gameObject.tag == "Platform")
            transform.parent = collision.transform;
    }

    private void OnTriggerExit2D(Collider2D collision)
    {
        if (collision.gameObject.tag == "Platform")
            transform.parent = null;
    }

}
