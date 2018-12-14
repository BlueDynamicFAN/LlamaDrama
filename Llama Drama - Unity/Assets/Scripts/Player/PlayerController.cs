using UnityEngine;

public class PlayerController : PhysicsObject
{
    public float jumpStrength;
    public float maxSpeed;

    private AudioSource audio;
    private bool HasJumped = false;
    private Animator animator;
    private SpriteRenderer sr;

    private void Start()
    {
        audio = GetComponent<AudioSource>();
        animator = GetComponent<Animator>();
        sr = GetComponent<SpriteRenderer>();
    }

    protected override void ComputeVelocity()
    {
        Vector2 move = Vector2.zero;

        move.x = Input.GetAxis("Horizontal");

        if (Input.GetButtonDown("Jump") && grounded)
        {
            velocity.y = jumpStrength;
            HasJumped = true;
        }

        if (!grounded)
            targetVelocity = move * (maxSpeed * 0.8f);
        else if (grounded)
            targetVelocity = move * maxSpeed;

        if(HasJumped)
        {
            audio.Play();
            HasJumped = false;
        }
    }

    void LateUpdate()
    {
        var vertical = Input.GetAxis("Vertical");
        var horizontal = Input.GetAxis("Horizontal");

        if (vertical > 0)
        {
            animator.SetInteger("Direction", 3);
        }
        else if (horizontal > 0)
        {
            sr.flipX = false;
            animator.SetInteger("Direction", 2);
        }
        else if (horizontal < 0)
        {
            sr.flipX = true;
            animator.SetInteger("Direction", 1);
        }
        else
            animator.SetInteger("Direction", 0);

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
