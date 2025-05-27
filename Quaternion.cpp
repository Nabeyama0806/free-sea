#include "Vector3.h"
#include "Quaternion.h"

Quaternion::operator MATRIX() const
{
	MATRIX mat;
	float xx2 = 2 * x * x;
	float yy2 = 2 * y * y;
	float zz2 = 2 * z * z;
	float xy2 = 2 * x * y;
	float xz2 = 2 * x * z;
	float yz2 = 2 * y * z;
	float wx2 = 2 * w * x;
	float wy2 = 2 * w * y;
	float wz2 = 2 * w * z;

	// �s��ւ̐ݒ�
	mat.m[0][0] = 1 - yy2 - zz2;
	mat.m[0][1] = xy2 + wz2;
	mat.m[0][2] = xz2 - wy2;
	mat.m[0][3] = 0;
	mat.m[1][0] = xy2 - wz2;
	mat.m[1][1] = 1 - xx2 - zz2;
	mat.m[1][2] = yz2 + wx2;
	mat.m[1][3] = 0;
	mat.m[2][0] = xz2 + wy2;
	mat.m[2][1] = yz2 - wx2;
	mat.m[2][2] = 1 - xx2 - yy2;
	mat.m[2][3] = 0;
	mat.m[3][0] = 0;
	mat.m[3][1] = 0;
	mat.m[3][2] = 0;
	mat.m[3][3] = 1;

	return mat;
}

//���ʐ��`��Ԃ��s��(t��0�`1)
Quaternion Quaternion::Slerp(const Quaternion &from, Quaternion to, float t)
{
	// 2�̉�]�̓��ς����߂�
	float dot = Dot(from, to);

	// ���ς����̎��A�ŒZ�����ł̕�Ԃ𓾂邽�߂ɕЕ��𕉂ɂ���
	if (dot < 0)
	{
		to = Quaternion(-to.x, -to.y, -to.z, -to.w);
		dot = -dot;
	}

	if (dot < 0.9995f)
	{
		float angle = std::acosf(dot);
		float s = 1.0f / std::sinf(angle);
		float w1 = std::sinf(angle * (1.0f - t)) * s;
		float w2 = std::sinf(angle * t) * s;

		return Quaternion(
			from.x * w1 + to.x * w2,
			from.y * w1 + to.y * w2,
			from.z * w1 + to.z * w2,
			from.w * w1 + to.w * w2
		).Normalized();
	}
	return to;
}

//�C�ӎ���]�̎l�����̍쐬
Quaternion Quaternion::AngleAxis(float rad, Vector3 axis)
{
	// �x�N�g���̐��K��
	axis.Normalize();

	// ��`�ɏ]���Đ�����ݒ肷��
	return Quaternion(
		axis.x * std::sinf(rad / 2),
		axis.y * std::sinf(rad / 2),
		axis.z * std::sinf(rad / 2),
		std::cosf(rad / 2)
	);
}

//������ύX���邽�߂̉�]�̎l�����̍쐬(2�̃x�N�g����180�x�̏ꍇ�͖���`)
Quaternion Quaternion::FromToRotation(const Vector3& from, const Vector3& to)
{
	// �O�ς�p���āA���x�N�g�������߂�
	Vector3 axis = Vector3::Cross(from, to);

	// �O�ς�(0,0,0)�̎��́A����]�̃N�H�[�^�j�I��(0,0,0,1)�ɂ���
	if (axis.IsZero())
	{
		if (Vector3::Dot(from, to) < 0)
		{
			// Y���Ő^���΂�����
			return AngleAxis(Math::DegToRad(180.0f), Vector3(0, 1, 0));
		}
		else
		{
			return Quaternion();
		}
	}

	// ���ς̒�`�����]�ʂ����߂� a�Eb = |a||b|cos�� �Ȃ̂�
	float rad = std::acosf(Vector3::Dot(from, to) / (from.Magnitude() * to.Magnitude()));

	// ���߂����Ɖ�]�ʂŃN�H�[�^�j�I���̐���
	return AngleAxis(rad, axis);
}

//�C�ӎ���]�̎l�����̐ݒ�
void Quaternion::SetRotationAxis(float rad, const Vector3& axis)
{
	*this = AngleAxis(rad, axis);
}

//������ύX���邽�߂̉�]�̎l�����̐ݒ�(2�̃x�N�g����180�x�̏ꍇ�͖���`)
void Quaternion::SetRotationDirection(Vector3 from, Vector3 to)
{
	*this = FromToRotation(from, to);
}

Quaternion Quaternion::LookRotation(const Vector3& forward)
{
	// �I�u�W�F�N�g�̐��ʂ���forward�Ɍ������]���擾
	Quaternion lookRotation = FromToRotation(Vector3(0, 0, -1), forward);
	// �O�ς�p����upwards��forward�ɐ����ȃx�N�g��(�Ԏ�)�𓾂�
	Vector3 xAxisHorizontal = Vector3::Cross(Vector3(0, 1, 0), forward);
	// ��]���y��(�Ύ�)�����߂�
	Vector3 yAxisAfterRotate = Vector3::Cross(forward, xAxisHorizontal);

	// Look���y��(��) ���� ��]���y��(��) �֏C�������]�����߂�
	Vector3 yAxisBeforeModify = lookRotation * Vector3(0, 1, 0);
	Quaternion modifyRotation = FromToRotation(yAxisBeforeModify, yAxisAfterRotate);

	// ��]���������ĕԂ�
	return modifyRotation * lookRotation;
}
