using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class HorizontalMovement : MonoBehaviour
{
    private Vector3 startPos;
    private Vector3 targetPos;
    public float speed;
    public int direction;
    private bool moveSideways;
    private GameObject target = null;
    private Vector3 offset;

    void Start()
    {
        startPos = transform.position;

        if(direction == 0)  // right
            targetPos = new Vector3(startPos.x + 18, startPos.y, startPos.z);
        else                // left
            targetPos = new Vector3(startPos.x - 18, startPos.y, startPos.z);

        moveSideways = true;
    }

    void Update()
    {
        float step = speed * Time.deltaTime;
        if (transform.position == targetPos)
        {
            moveSideways = false;
        }
        else if (transform.position == startPos)
        {
            moveSideways = true;
        }
        if (moveSideways == false)
        {
            transform.position = Vector3.MoveTowards(transform.position, startPos, step);
        }
        else if (moveSideways)
        {
            transform.position = Vector3.MoveTowards(transform.position, targetPos, step);
        }
    }

    private void OnTriggerStay2D(Collider2D collision)
    {
        target = collision.gameObject;
        offset = target.transform.position - transform.position;
    }

    void OnTriggerExit2D(Collider2D col)
    {
        target = null;
    }

    void LateUpdate()
    {
        if (target != null)
        {
            target.transform.position = transform.position + offset;
        }
    }

}